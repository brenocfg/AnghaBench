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
struct spi_nor {int /*<<< orphan*/  lock; int /*<<< orphan*/  (* unprepare ) (struct spi_nor*,int) ;} ;
typedef  enum spi_nor_ops { ____Placeholder_spi_nor_ops } spi_nor_ops ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct spi_nor*,int) ; 

__attribute__((used)) static void spi_nor_unlock_and_unprep(struct spi_nor *nor, enum spi_nor_ops ops)
{
	if (nor->unprepare)
		nor->unprepare(nor, ops);
	mutex_unlock(&nor->lock);
}