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
typedef  scalar_t__ u8 ;
struct imon_context {scalar_t__ kc; scalar_t__ last_keycode; unsigned char rc_toggle; int /*<<< orphan*/  kc_lock; scalar_t__ release_code; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IMON_KEY_MCE ; 
 scalar_t__ KEY_RESERVED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int imon_parse_press_type(struct imon_context *ictx,
				 unsigned char *buf, u8 ktype)
{
	int press_type = 0;
	unsigned long flags;

	spin_lock_irqsave(&ictx->kc_lock, flags);

	/* key release of 0x02XXXXXX key */
	if (ictx->kc == KEY_RESERVED && buf[0] == 0x02 && buf[3] == 0x00)
		ictx->kc = ictx->last_keycode;

	/* mouse button release on (some) 0xffdc devices */
	else if (ictx->kc == KEY_RESERVED && buf[0] == 0x68 && buf[1] == 0x82 &&
		 buf[2] == 0x81 && buf[3] == 0xb7)
		ictx->kc = ictx->last_keycode;

	/* mouse button release on (some other) 0xffdc devices */
	else if (ictx->kc == KEY_RESERVED && buf[0] == 0x01 && buf[1] == 0x00 &&
		 buf[2] == 0x81 && buf[3] == 0xb7)
		ictx->kc = ictx->last_keycode;

	/* mce-specific button handling, no keyup events */
	else if (ktype == IMON_KEY_MCE) {
		ictx->rc_toggle = buf[2];
		press_type = 1;

	/* incoherent or irrelevant data */
	} else if (ictx->kc == KEY_RESERVED)
		press_type = -EINVAL;

	/* key release of 0xXXXXXXb7 key */
	else if (ictx->release_code)
		press_type = 0;

	/* this is a button press */
	else
		press_type = 1;

	spin_unlock_irqrestore(&ictx->kc_lock, flags);

	return press_type;
}