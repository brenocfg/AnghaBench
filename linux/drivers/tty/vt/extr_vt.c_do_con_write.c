#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int u16 ;
struct vt_notifier_param {int c; struct vc_data* vc; } ;
struct vc_data {unsigned int vc_num; int vc_hi_font_mask; scalar_t__ vc_state; int vc_utf_count; int vc_utf_char; int vc_npar; unsigned char vc_attr; unsigned long vc_pos; int vc_x; int vc_cols; scalar_t__ vc_decawm; scalar_t__ vc_need_wrap; scalar_t__ vc_decim; int /*<<< orphan*/  vc_can_do_color; scalar_t__ vc_disp_ctrl; scalar_t__ vc_utf; } ;
struct tty_struct {int /*<<< orphan*/  stopped; struct vc_data* driver_data; } ;

/* Variables and functions */
 int CTRL_ACTION ; 
 int CTRL_ALWAYS ; 
 scalar_t__ ESnormal ; 
 scalar_t__ NOTIFY_STOP ; 
 int /*<<< orphan*/  VT_PREWRITE ; 
 scalar_t__ atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vt_notifier_param*) ; 
 int /*<<< orphan*/  con_flush (struct vc_data*,unsigned long,unsigned long,int*) ; 
 scalar_t__ con_is_fg (struct vc_data*) ; 
 scalar_t__ con_should_update (struct vc_data*) ; 
 int /*<<< orphan*/  console_conditional_schedule () ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int conv_uni_to_pc (struct vc_data*,char) ; 
 int /*<<< orphan*/  cr (struct vc_data*) ; 
 int /*<<< orphan*/  do_con_trol (struct tty_struct*,struct vc_data*,int) ; 
 int /*<<< orphan*/  hide_cursor (struct vc_data*) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  insert_char (struct vc_data*,int) ; 
 scalar_t__ is_double_width (int) ; 
 int /*<<< orphan*/  lf (struct vc_data*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  notify_update (struct vc_data*) ; 
 int /*<<< orphan*/  notify_write (struct vc_data*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn_once (char*,unsigned int) ; 
 int /*<<< orphan*/  scr_writew (unsigned char,int*) ; 
 int /*<<< orphan*/  vc_cons_allocated (unsigned int) ; 
 int vc_translate (struct vc_data*,int) ; 
 int /*<<< orphan*/  vc_uniscr_debug_check (struct vc_data*) ; 
 int /*<<< orphan*/  vc_uniscr_putc (struct vc_data*,int) ; 
 int /*<<< orphan*/  vt_notifier_list ; 

__attribute__((used)) static int do_con_write(struct tty_struct *tty, const unsigned char *buf, int count)
{
	int c, next_c, tc, ok, n = 0, draw_x = -1;
	unsigned int currcons;
	unsigned long draw_from = 0, draw_to = 0;
	struct vc_data *vc;
	unsigned char vc_attr;
	struct vt_notifier_param param;
	uint8_t rescan;
	uint8_t inverse;
	uint8_t width;
	u16 himask, charmask;

	if (in_interrupt())
		return count;

	might_sleep();

	console_lock();
	vc = tty->driver_data;
	if (vc == NULL) {
		pr_err("vt: argh, driver_data is NULL !\n");
		console_unlock();
		return 0;
	}

	currcons = vc->vc_num;
	if (!vc_cons_allocated(currcons)) {
		/* could this happen? */
		pr_warn_once("con_write: tty %d not allocated\n", currcons+1);
		console_unlock();
		return 0;
	}

	himask = vc->vc_hi_font_mask;
	charmask = himask ? 0x1ff : 0xff;

	/* undraw cursor first */
	if (con_is_fg(vc))
		hide_cursor(vc);

	param.vc = vc;

	while (!tty->stopped && count) {
		int orig = *buf;
		c = orig;
		buf++;
		n++;
		count--;
		rescan = 0;
		inverse = 0;
		width = 1;

		/* Do no translation at all in control states */
		if (vc->vc_state != ESnormal) {
			tc = c;
		} else if (vc->vc_utf && !vc->vc_disp_ctrl) {
		    /* Combine UTF-8 into Unicode in vc_utf_char.
		     * vc_utf_count is the number of continuation bytes still
		     * expected to arrive.
		     * vc_npar is the number of continuation bytes arrived so
		     * far
		     */
rescan_last_byte:
		    if ((c & 0xc0) == 0x80) {
			/* Continuation byte received */
			static const uint32_t utf8_length_changes[] = { 0x0000007f, 0x000007ff, 0x0000ffff, 0x001fffff, 0x03ffffff, 0x7fffffff };
			if (vc->vc_utf_count) {
			    vc->vc_utf_char = (vc->vc_utf_char << 6) | (c & 0x3f);
			    vc->vc_npar++;
			    if (--vc->vc_utf_count) {
				/* Still need some bytes */
				continue;
			    }
			    /* Got a whole character */
			    c = vc->vc_utf_char;
			    /* Reject overlong sequences */
			    if (c <= utf8_length_changes[vc->vc_npar - 1] ||
					c > utf8_length_changes[vc->vc_npar])
				c = 0xfffd;
			} else {
			    /* Unexpected continuation byte */
			    vc->vc_utf_count = 0;
			    c = 0xfffd;
			}
		    } else {
			/* Single ASCII byte or first byte of a sequence received */
			if (vc->vc_utf_count) {
			    /* Continuation byte expected */
			    rescan = 1;
			    vc->vc_utf_count = 0;
			    c = 0xfffd;
			} else if (c > 0x7f) {
			    /* First byte of a multibyte sequence received */
			    vc->vc_npar = 0;
			    if ((c & 0xe0) == 0xc0) {
				vc->vc_utf_count = 1;
				vc->vc_utf_char = (c & 0x1f);
			    } else if ((c & 0xf0) == 0xe0) {
				vc->vc_utf_count = 2;
				vc->vc_utf_char = (c & 0x0f);
			    } else if ((c & 0xf8) == 0xf0) {
				vc->vc_utf_count = 3;
				vc->vc_utf_char = (c & 0x07);
			    } else if ((c & 0xfc) == 0xf8) {
				vc->vc_utf_count = 4;
				vc->vc_utf_char = (c & 0x03);
			    } else if ((c & 0xfe) == 0xfc) {
				vc->vc_utf_count = 5;
				vc->vc_utf_char = (c & 0x01);
			    } else {
				/* 254 and 255 are invalid */
				c = 0xfffd;
			    }
			    if (vc->vc_utf_count) {
				/* Still need some bytes */
				continue;
			    }
			}
			/* Nothing to do if an ASCII byte was received */
		    }
		    /* End of UTF-8 decoding. */
		    /* c is the received character, or U+FFFD for invalid sequences. */
		    /* Replace invalid Unicode code points with U+FFFD too */
		    if ((c >= 0xd800 && c <= 0xdfff) || c == 0xfffe || c == 0xffff)
			c = 0xfffd;
		    tc = c;
		} else {	/* no utf or alternate charset mode */
		    tc = vc_translate(vc, c);
		}

		param.c = tc;
		if (atomic_notifier_call_chain(&vt_notifier_list, VT_PREWRITE,
					&param) == NOTIFY_STOP)
			continue;

                /* If the original code was a control character we
                 * only allow a glyph to be displayed if the code is
                 * not normally used (such as for cursor movement) or
                 * if the disp_ctrl mode has been explicitly enabled.
                 * Certain characters (as given by the CTRL_ALWAYS
                 * bitmap) are always displayed as control characters,
                 * as the console would be pretty useless without
                 * them; to display an arbitrary font position use the
                 * direct-to-font zone in UTF-8 mode.
                 */
                ok = tc && (c >= 32 ||
			    !(vc->vc_disp_ctrl ? (CTRL_ALWAYS >> c) & 1 :
				  vc->vc_utf || ((CTRL_ACTION >> c) & 1)))
			&& (c != 127 || vc->vc_disp_ctrl)
			&& (c != 128+27);

		if (vc->vc_state == ESnormal && ok) {
			if (vc->vc_utf && !vc->vc_disp_ctrl) {
				if (is_double_width(c))
					width = 2;
			}
			/* Now try to find out how to display it */
			tc = conv_uni_to_pc(vc, tc);
			if (tc & ~charmask) {
				if (tc == -1 || tc == -2) {
				    continue; /* nothing to display */
				}
				/* Glyph not found */
				if ((!(vc->vc_utf && !vc->vc_disp_ctrl) || c < 128) && !(c & ~charmask)) {
				    /* In legacy mode use the glyph we get by a 1:1 mapping.
				       This would make absolutely no sense with Unicode in mind,
				       but do this for ASCII characters since a font may lack
				       Unicode mapping info and we don't want to end up with
				       having question marks only. */
				    tc = c;
				} else {
				    /* Display U+FFFD. If it's not found, display an inverse question mark. */
				    tc = conv_uni_to_pc(vc, 0xfffd);
				    if (tc < 0) {
					inverse = 1;
					tc = conv_uni_to_pc(vc, '?');
					if (tc < 0) tc = '?';
				    }
				}
			}

			if (!inverse) {
				vc_attr = vc->vc_attr;
			} else {
				/* invert vc_attr */
				if (!vc->vc_can_do_color) {
					vc_attr = (vc->vc_attr) ^ 0x08;
				} else if (vc->vc_hi_font_mask == 0x100) {
					vc_attr = ((vc->vc_attr) & 0x11) | (((vc->vc_attr) & 0xe0) >> 4) | (((vc->vc_attr) & 0x0e) << 4);
				} else {
					vc_attr = ((vc->vc_attr) & 0x88) | (((vc->vc_attr) & 0x70) >> 4) | (((vc->vc_attr) & 0x07) << 4);
				}
				con_flush(vc, draw_from, draw_to, &draw_x);
			}

			next_c = c;
			while (1) {
				if (vc->vc_need_wrap || vc->vc_decim)
					con_flush(vc, draw_from, draw_to,
							&draw_x);
				if (vc->vc_need_wrap) {
					cr(vc);
					lf(vc);
				}
				if (vc->vc_decim)
					insert_char(vc, 1);
				vc_uniscr_putc(vc, next_c);
				scr_writew(himask ?
					     ((vc_attr << 8) & ~himask) + ((tc & 0x100) ? himask : 0) + (tc & 0xff) :
					     (vc_attr << 8) + tc,
					   (u16 *) vc->vc_pos);
				if (con_should_update(vc) && draw_x < 0) {
					draw_x = vc->vc_x;
					draw_from = vc->vc_pos;
				}
				if (vc->vc_x == vc->vc_cols - 1) {
					vc->vc_need_wrap = vc->vc_decawm;
					draw_to = vc->vc_pos + 2;
				} else {
					vc->vc_x++;
					draw_to = (vc->vc_pos += 2);
				}

				if (!--width) break;

				tc = conv_uni_to_pc(vc, ' '); /* A space is printed in the second column */
				if (tc < 0) tc = ' ';
				next_c = ' ';
			}
			notify_write(vc, c);

			if (inverse)
				con_flush(vc, draw_from, draw_to, &draw_x);

			if (rescan) {
				rescan = 0;
				inverse = 0;
				width = 1;
				c = orig;
				goto rescan_last_byte;
			}
			continue;
		}
		con_flush(vc, draw_from, draw_to, &draw_x);
		do_con_trol(tty, vc, orig);
	}
	con_flush(vc, draw_from, draw_to, &draw_x);
	vc_uniscr_debug_check(vc);
	console_conditional_schedule();
	notify_update(vc);
	console_unlock();
	return n;
}