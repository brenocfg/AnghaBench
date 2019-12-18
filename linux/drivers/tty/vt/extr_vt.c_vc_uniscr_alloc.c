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
struct uni_screen {void** lines; } ;
typedef  int /*<<< orphan*/  char32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct uni_screen *vc_uniscr_alloc(unsigned int cols, unsigned int rows)
{
	struct uni_screen *uniscr;
	void *p;
	unsigned int memsize, i;

	/* allocate everything in one go */
	memsize = cols * rows * sizeof(char32_t);
	memsize += rows * sizeof(char32_t *);
	p = kmalloc(memsize, GFP_KERNEL);
	if (!p)
		return NULL;

	/* initial line pointers */
	uniscr = p;
	p = uniscr->lines + rows;
	for (i = 0; i < rows; i++) {
		uniscr->lines[i] = p;
		p += cols * sizeof(char32_t);
	}
	return uniscr;
}