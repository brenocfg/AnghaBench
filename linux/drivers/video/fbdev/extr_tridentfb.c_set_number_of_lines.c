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
 int /*<<< orphan*/  CyberEnhance ; 
 int read3CE (struct tridentfb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write3CE (struct tridentfb_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_number_of_lines(struct tridentfb_par *par, int lines)
{
	int tmp = read3CE(par, CyberEnhance) & 0x8F;
	if (lines > 1024)
		tmp |= 0x50;
	else if (lines > 768)
		tmp |= 0x30;
	else if (lines > 600)
		tmp |= 0x20;
	else if (lines > 480)
		tmp |= 0x10;
	write3CE(par, CyberEnhance, tmp);
}