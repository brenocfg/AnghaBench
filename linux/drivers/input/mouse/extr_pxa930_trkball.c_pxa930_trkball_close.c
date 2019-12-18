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
struct pxa930_trkball {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct pxa930_trkball* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  pxa930_trkball_disable (struct pxa930_trkball*) ; 

__attribute__((used)) static void pxa930_trkball_close(struct input_dev *dev)
{
	struct pxa930_trkball *trkball = input_get_drvdata(dev);

	pxa930_trkball_disable(trkball);
}