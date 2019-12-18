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
typedef  int /*<<< orphan*/  u8 ;
struct pegasus {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  NOTETAKER_SET_CMD ; 
 int /*<<< orphan*/  NOTETAKER_SET_MODE ; 
 int pegasus_control_msg (struct pegasus*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pegasus_set_mode(struct pegasus *pegasus, u8 mode, u8 led)
{
	u8 cmd[] = { NOTETAKER_SET_CMD, NOTETAKER_SET_MODE, led, mode };

	return pegasus_control_msg(pegasus, cmd, sizeof(cmd));
}