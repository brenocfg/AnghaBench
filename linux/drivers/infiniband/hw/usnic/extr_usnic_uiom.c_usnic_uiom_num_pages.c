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
struct usnic_uiom_reg {scalar_t__ offset; scalar_t__ length; } ;

/* Variables and functions */
 size_t PAGE_ALIGN (scalar_t__) ; 
 size_t PAGE_SHIFT ; 

__attribute__((used)) static inline size_t usnic_uiom_num_pages(struct usnic_uiom_reg *uiomr)
{
	return PAGE_ALIGN(uiomr->length + uiomr->offset) >> PAGE_SHIFT;
}