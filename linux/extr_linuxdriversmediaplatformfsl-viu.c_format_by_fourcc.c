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
struct viu_fmt {int pixelformat; } ;

/* Variables and functions */
 int NUM_FORMATS ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,char*) ; 
 struct viu_fmt* formats ; 

__attribute__((used)) static struct viu_fmt *format_by_fourcc(int fourcc)
{
	int i;

	for (i = 0; i < NUM_FORMATS; i++) {
		if (formats[i].pixelformat == fourcc)
			return formats + i;
	}

	dprintk(0, "unknown pixelformat:'%4.4s'\n", (char *)&fourcc);
	return NULL;
}