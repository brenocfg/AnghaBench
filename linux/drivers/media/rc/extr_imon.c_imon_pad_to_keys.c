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
typedef  int u32 ;
typedef  int u16 ;
struct imon_context {int product; scalar_t__ rc_proto; int /*<<< orphan*/  kc_lock; void* kc; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int KEY_RESERVED ; 
 void* KEY_UNKNOWN ; 
 scalar_t__ RC_PROTO_BIT_IMON ; 
 scalar_t__ abs (char) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* imon_remote_key_lookup (struct imon_context*,int) ; 
 scalar_t__ pad_stabilize ; 
 int pad_thresh ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stabilize (int,int,int,int) ; 

__attribute__((used)) static void imon_pad_to_keys(struct imon_context *ictx, unsigned char *buf)
{
	int dir = 0;
	signed char rel_x = 0x00, rel_y = 0x00;
	u16 timeout, threshold;
	u32 scancode = KEY_RESERVED;
	unsigned long flags;

	/*
	 * The imon directional pad functions more like a touchpad. Bytes 3 & 4
	 * contain a position coordinate (x,y), with each component ranging
	 * from -14 to 14. We want to down-sample this to only 4 discrete values
	 * for up/down/left/right arrow keys. Also, when you get too close to
	 * diagonals, it has a tendency to jump back and forth, so lets try to
	 * ignore when they get too close.
	 */
	if (ictx->product != 0xffdc) {
		/* first, pad to 8 bytes so it conforms with everything else */
		buf[5] = buf[6] = buf[7] = 0;
		timeout = 500;	/* in msecs */
		/* (2*threshold) x (2*threshold) square */
		threshold = pad_thresh ? pad_thresh : 28;
		rel_x = buf[2];
		rel_y = buf[3];

		if (ictx->rc_proto == RC_PROTO_BIT_IMON && pad_stabilize) {
			if ((buf[1] == 0) && ((rel_x != 0) || (rel_y != 0))) {
				dir = stabilize((int)rel_x, (int)rel_y,
						timeout, threshold);
				if (!dir) {
					spin_lock_irqsave(&ictx->kc_lock,
							  flags);
					ictx->kc = KEY_UNKNOWN;
					spin_unlock_irqrestore(&ictx->kc_lock,
							       flags);
					return;
				}
				buf[2] = dir & 0xFF;
				buf[3] = (dir >> 8) & 0xFF;
				scancode = be32_to_cpu(*((__be32 *)buf));
			}
		} else {
			/*
			 * Hack alert: instead of using keycodes, we have
			 * to use hard-coded scancodes here...
			 */
			if (abs(rel_y) > abs(rel_x)) {
				buf[2] = (rel_y > 0) ? 0x7F : 0x80;
				buf[3] = 0;
				if (rel_y > 0)
					scancode = 0x01007f00; /* KEY_DOWN */
				else
					scancode = 0x01008000; /* KEY_UP */
			} else {
				buf[2] = 0;
				buf[3] = (rel_x > 0) ? 0x7F : 0x80;
				if (rel_x > 0)
					scancode = 0x0100007f; /* KEY_RIGHT */
				else
					scancode = 0x01000080; /* KEY_LEFT */
			}
		}

	/*
	 * Handle on-board decoded pad events for e.g. older VFD/iMON-Pad
	 * device (15c2:ffdc). The remote generates various codes from
	 * 0x68nnnnB7 to 0x6AnnnnB7, the left mouse button generates
	 * 0x688301b7 and the right one 0x688481b7. All other keys generate
	 * 0x2nnnnnnn. Position coordinate is encoded in buf[1] and buf[2] with
	 * reversed endianness. Extract direction from buffer, rotate endianness,
	 * adjust sign and feed the values into stabilize(). The resulting codes
	 * will be 0x01008000, 0x01007F00, which match the newer devices.
	 */
	} else {
		timeout = 10;	/* in msecs */
		/* (2*threshold) x (2*threshold) square */
		threshold = pad_thresh ? pad_thresh : 15;

		/* buf[1] is x */
		rel_x = (buf[1] & 0x08) | (buf[1] & 0x10) >> 2 |
			(buf[1] & 0x20) >> 4 | (buf[1] & 0x40) >> 6;
		if (buf[0] & 0x02)
			rel_x |= ~0x10+1;
		/* buf[2] is y */
		rel_y = (buf[2] & 0x08) | (buf[2] & 0x10) >> 2 |
			(buf[2] & 0x20) >> 4 | (buf[2] & 0x40) >> 6;
		if (buf[0] & 0x01)
			rel_y |= ~0x10+1;

		buf[0] = 0x01;
		buf[1] = buf[4] = buf[5] = buf[6] = buf[7] = 0;

		if (ictx->rc_proto == RC_PROTO_BIT_IMON && pad_stabilize) {
			dir = stabilize((int)rel_x, (int)rel_y,
					timeout, threshold);
			if (!dir) {
				spin_lock_irqsave(&ictx->kc_lock, flags);
				ictx->kc = KEY_UNKNOWN;
				spin_unlock_irqrestore(&ictx->kc_lock, flags);
				return;
			}
			buf[2] = dir & 0xFF;
			buf[3] = (dir >> 8) & 0xFF;
			scancode = be32_to_cpu(*((__be32 *)buf));
		} else {
			/*
			 * Hack alert: instead of using keycodes, we have
			 * to use hard-coded scancodes here...
			 */
			if (abs(rel_y) > abs(rel_x)) {
				buf[2] = (rel_y > 0) ? 0x7F : 0x80;
				buf[3] = 0;
				if (rel_y > 0)
					scancode = 0x01007f00; /* KEY_DOWN */
				else
					scancode = 0x01008000; /* KEY_UP */
			} else {
				buf[2] = 0;
				buf[3] = (rel_x > 0) ? 0x7F : 0x80;
				if (rel_x > 0)
					scancode = 0x0100007f; /* KEY_RIGHT */
				else
					scancode = 0x01000080; /* KEY_LEFT */
			}
		}
	}

	if (scancode) {
		spin_lock_irqsave(&ictx->kc_lock, flags);
		ictx->kc = imon_remote_key_lookup(ictx, scancode);
		spin_unlock_irqrestore(&ictx->kc_lock, flags);
	}
}