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
struct ocxl_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_spa (struct ocxl_link*) ; 
 int /*<<< orphan*/  kfree (struct ocxl_link*) ; 
 int /*<<< orphan*/  release_xsl_irq (struct ocxl_link*) ; 

__attribute__((used)) static void free_link(struct ocxl_link *link)
{
	release_xsl_irq(link);
	free_spa(link);
	kfree(link);
}