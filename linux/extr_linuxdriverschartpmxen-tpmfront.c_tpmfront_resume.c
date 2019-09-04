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
struct xenbus_device {int dummy; } ;

/* Variables and functions */
 int tpmfront_probe (struct xenbus_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpmfront_remove (struct xenbus_device*) ; 

__attribute__((used)) static int tpmfront_resume(struct xenbus_device *dev)
{
	/* A suspend/resume/migrate will interrupt a vTPM anyway */
	tpmfront_remove(dev);
	return tpmfront_probe(dev, NULL);
}