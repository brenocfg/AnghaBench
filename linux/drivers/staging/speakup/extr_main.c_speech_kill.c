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
struct TYPE_3__ {char (* is_alive ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_IAM_ALIVE ; 
 int /*<<< orphan*/  MSG_YOU_KILLED_SPEAKUP ; 
 scalar_t__ spk_killed ; 
 int /*<<< orphan*/  spk_msg_get (int /*<<< orphan*/ ) ; 
 int spk_shut_up ; 
 char stub1 (TYPE_1__*) ; 
 TYPE_1__* synth ; 
 int /*<<< orphan*/  synth_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void speech_kill(struct vc_data *vc)
{
	char val = synth->is_alive(synth);

	if (val == 0)
		return;

	/* re-enables synth, if disabled */
	if (val == 2 || spk_killed) {
		/* dead */
		spk_shut_up &= ~0x40;
		synth_printf("%s\n", spk_msg_get(MSG_IAM_ALIVE));
	} else {
		synth_printf("%s\n", spk_msg_get(MSG_YOU_KILLED_SPEAKUP));
		spk_shut_up |= 0x40;
	}
}