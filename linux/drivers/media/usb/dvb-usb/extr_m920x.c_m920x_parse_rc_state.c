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
typedef  int u8 ;
struct m920x_state {int rep_count; } ;
struct dvb_usb_device {struct m920x_state* priv; } ;

/* Variables and functions */
 int REMOTE_KEY_PRESSED ; 
 int REMOTE_KEY_REPEAT ; 
 int REMOTE_NO_KEY_PRESSED ; 
 int /*<<< orphan*/  deb (char*,int) ; 

__attribute__((used)) static inline void m920x_parse_rc_state(struct dvb_usb_device *d, u8 rc_state,
					int *state)
{
	struct m920x_state *m = d->priv;

	switch (rc_state) {
	case 0x80:
		*state = REMOTE_NO_KEY_PRESSED;
		break;

	case 0x88: /* framing error or "invalid code" */
	case 0x99:
	case 0xc0:
	case 0xd8:
		*state = REMOTE_NO_KEY_PRESSED;
		m->rep_count = 0;
		break;

	case 0x93:
	case 0x92:
	case 0x83: /* pinnacle PCTV310e */
	case 0x82:
		m->rep_count = 0;
		*state = REMOTE_KEY_PRESSED;
		break;

	case 0x91:
	case 0x81: /* pinnacle PCTV310e */
		/* prevent immediate auto-repeat */
		if (++m->rep_count > 2)
			*state = REMOTE_KEY_REPEAT;
		else
			*state = REMOTE_NO_KEY_PRESSED;
		break;

	default:
		deb("Unexpected rc state %02x\n", rc_state);
		*state = REMOTE_NO_KEY_PRESSED;
		break;
	}
}