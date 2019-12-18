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
struct cx88_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_INIT ; 
 int /*<<< orphan*/  AUD_INIT_LD ; 
 int /*<<< orphan*/  AUD_SOFT_RESET ; 
 int /*<<< orphan*/  AUD_VOL_CTL ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_audio_start(struct cx88_core *core, u32 mode)
{
	/* mute */
	cx_write(AUD_VOL_CTL, (1 << 6));

	/* start programming */
	cx_write(AUD_INIT, mode);
	cx_write(AUD_INIT_LD, 0x0001);
	cx_write(AUD_SOFT_RESET, 0x0001);
}