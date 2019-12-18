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
struct tridentfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HorStretch ; 
 int /*<<< orphan*/  VertStretch ; 
 int read3CE (struct tridentfb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write3CE (struct tridentfb_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void screen_center(struct tridentfb_par *par)
{
	write3CE(par, VertStretch, (read3CE(par, VertStretch) & 0x7C) | 0x80);
	write3CE(par, HorStretch, (read3CE(par, HorStretch) & 0x7C) | 0x80);
}