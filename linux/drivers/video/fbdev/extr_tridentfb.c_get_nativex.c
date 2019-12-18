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
 int /*<<< orphan*/  VertStretch ; 
 int nativex ; 
 int /*<<< orphan*/  output (char*,int,int) ; 
 int read3CE (struct tridentfb_par*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_nativex(struct tridentfb_par *par)
{
	int x, y, tmp;

	if (nativex)
		return nativex;

	tmp = (read3CE(par, VertStretch) >> 4) & 3;

	switch (tmp) {
	case 0:
		x = 1280; y = 1024;
		break;
	case 2:
		x = 1024; y = 768;
		break;
	case 3:
		x = 800; y = 600;
		break;
	case 1:
	default:
		x = 640;  y = 480;
		break;
	}

	output("%dx%d flat panel found\n", x, y);
	return x;
}