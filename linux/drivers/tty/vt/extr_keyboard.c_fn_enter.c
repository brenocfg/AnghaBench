#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vc_data {int dummy; } ;
struct TYPE_3__ {scalar_t__ kbdmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CRLF ; 
 scalar_t__ VC_UNICODE ; 
 int conv_uni_to_8bit (scalar_t__) ; 
 scalar_t__ diacr ; 
 TYPE_1__* kbd ; 
 int /*<<< orphan*/  put_queue (struct vc_data*,int) ; 
 int /*<<< orphan*/  to_utf8 (struct vc_data*,scalar_t__) ; 
 scalar_t__ vc_kbd_mode (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fn_enter(struct vc_data *vc)
{
	if (diacr) {
		if (kbd->kbdmode == VC_UNICODE)
			to_utf8(vc, diacr);
		else {
			int c = conv_uni_to_8bit(diacr);
			if (c != -1)
				put_queue(vc, c);
		}
		diacr = 0;
	}

	put_queue(vc, 13);
	if (vc_kbd_mode(kbd, VC_CRLF))
		put_queue(vc, 10);
}