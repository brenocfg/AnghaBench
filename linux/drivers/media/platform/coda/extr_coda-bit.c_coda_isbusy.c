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
struct coda_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODA_REG_BIT_BUSY ; 
 unsigned long coda_read (struct coda_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long coda_isbusy(struct coda_dev *dev)
{
	return coda_read(dev, CODA_REG_BIT_BUSY);
}