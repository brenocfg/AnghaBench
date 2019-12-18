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
struct saa7146_format {int pixelformat; } ;
struct saa7146_dev {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct saa7146_format*) ; 
 int /*<<< orphan*/  DEB_D (char*,char*) ; 
 struct saa7146_format* formats ; 

struct saa7146_format* saa7146_format_by_fourcc(struct saa7146_dev *dev, int fourcc)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(formats); i++) {
		if (formats[i].pixelformat == fourcc) {
			return formats+i;
		}
	}

	DEB_D("unknown pixelformat:'%4.4s'\n", (char *)&fourcc);
	return NULL;
}