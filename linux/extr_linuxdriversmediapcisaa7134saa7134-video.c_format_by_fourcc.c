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
struct saa7134_format {unsigned int fourcc; } ;

/* Variables and functions */
 unsigned int FORMATS ; 
 struct saa7134_format* formats ; 

__attribute__((used)) static struct saa7134_format* format_by_fourcc(unsigned int fourcc)
{
	unsigned int i;

	for (i = 0; i < FORMATS; i++)
		if (formats[i].fourcc == fourcc)
			return formats+i;
	return NULL;
}