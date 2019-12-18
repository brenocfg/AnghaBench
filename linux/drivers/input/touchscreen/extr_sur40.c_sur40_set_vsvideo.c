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
struct sur40_state {int /*<<< orphan*/  vsvideo; } ;

/* Variables and functions */
 int /*<<< orphan*/  sur40_poke (struct sur40_state*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sur40_set_vsvideo(struct sur40_state *handle, u8 value)
{
	int i;

	for (i = 0; i < 4; i++)
		sur40_poke(handle, 0x1c+i, value);
	handle->vsvideo = value;
}