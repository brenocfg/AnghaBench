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
struct sym_nvram {scalar_t__ type; } ;
struct sym_device {struct sym_nvram* nvram; } ;

/* Variables and functions */
 int /*<<< orphan*/  sym_read_nvram (struct sym_device*,struct sym_nvram*) ; 

__attribute__((used)) static void sym_get_nvram(struct sym_device *devp, struct sym_nvram *nvp)
{
	devp->nvram = nvp;
	nvp->type = 0;

	sym_read_nvram(devp, nvp);
}