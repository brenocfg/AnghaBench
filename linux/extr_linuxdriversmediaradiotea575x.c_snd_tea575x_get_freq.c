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
typedef  int /*<<< orphan*/  u32 ;
struct snd_tea575x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_tea575x_read (struct snd_tea575x*) ; 
 int /*<<< orphan*/  snd_tea575x_val_to_freq (struct snd_tea575x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 snd_tea575x_get_freq(struct snd_tea575x *tea)
{
	return snd_tea575x_val_to_freq(tea, snd_tea575x_read(tea));
}