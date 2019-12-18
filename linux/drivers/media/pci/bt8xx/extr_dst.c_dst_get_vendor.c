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
struct dst_state {int /*<<< orphan*/ * vendor; int /*<<< orphan*/  rxbuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int dst_check_sum (int*,int) ; 
 scalar_t__ dst_command (struct dst_state*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,char,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dst_get_vendor(struct dst_state *state)
{
	u8 get_vendor[] = { 0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	get_vendor[7] = dst_check_sum(get_vendor, 7);
	if (dst_command(state, get_vendor, 8) < 0) {
		dprintk(2, "Unsupported Command\n");
		return -1;
	}
	memset(&state->vendor, '\0', 8);
	memcpy(&state->vendor, &state->rxbuffer, 7);
	pr_err("Vendor=[%s]\n", &state->vendor[0]);

	return 0;
}