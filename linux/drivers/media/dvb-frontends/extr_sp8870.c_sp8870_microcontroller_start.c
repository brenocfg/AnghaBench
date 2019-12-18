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
struct sp8870_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sp8870_readreg (struct sp8870_state*,int) ; 
 int /*<<< orphan*/  sp8870_writereg (struct sp8870_state*,int,int) ; 

__attribute__((used)) static void sp8870_microcontroller_start (struct sp8870_state* state)
{
	sp8870_writereg(state, 0x0F08, 0x000);
	sp8870_writereg(state, 0x0F09, 0x000);

	// microcontroller START
	sp8870_writereg(state, 0x0F00, 0x001);
	// not documented but if we don't read 0x0D01 out here
	// we don't get a correct data valid signal
	sp8870_readreg(state, 0x0D01);
}