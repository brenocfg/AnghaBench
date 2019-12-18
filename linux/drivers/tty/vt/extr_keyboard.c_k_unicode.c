#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vc_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ kbdmode; } ;

/* Variables and functions */
 scalar_t__ VC_UNICODE ; 
 int conv_uni_to_8bit (unsigned int) ; 
 int dead_key_next ; 
 int diacr ; 
 unsigned int handle_diacr (struct vc_data*,unsigned int) ; 
 TYPE_1__* kbd ; 
 int /*<<< orphan*/  put_queue (struct vc_data*,int) ; 
 int /*<<< orphan*/  to_utf8 (struct vc_data*,unsigned int) ; 

__attribute__((used)) static void k_unicode(struct vc_data *vc, unsigned int value, char up_flag)
{
	if (up_flag)
		return;		/* no action, if this is a key release */

	if (diacr)
		value = handle_diacr(vc, value);

	if (dead_key_next) {
		dead_key_next = false;
		diacr = value;
		return;
	}
	if (kbd->kbdmode == VC_UNICODE)
		to_utf8(vc, value);
	else {
		int c = conv_uni_to_8bit(value);
		if (c != -1)
			put_queue(vc, c);
	}
}