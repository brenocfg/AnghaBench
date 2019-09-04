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
struct eni_tx {int /*<<< orphan*/  send; } ;
struct eni_dev {struct eni_tx* tx; } ;

/* Variables and functions */
 int NR_CHAN ; 

__attribute__((used)) static struct eni_tx *alloc_tx(struct eni_dev *eni_dev,int ubr)
{
	int i;

	for (i = !ubr; i < NR_CHAN; i++)
		if (!eni_dev->tx[i].send) return eni_dev->tx+i;
	return NULL;
}