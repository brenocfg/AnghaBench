#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct mpl115_data {int b1; int c12; int a0; int b2; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MPL115_PADC ; 
 int /*<<< orphan*/  MPL115_TADC ; 
 int mpl115_request (struct mpl115_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpl115_comp_pressure(struct mpl115_data *data, int *val, int *val2)
{
	int ret;
	u16 padc, tadc;
	int a1, y1, pcomp;
	unsigned kpa;

	mutex_lock(&data->lock);
	ret = mpl115_request(data);
	if (ret < 0)
		goto done;

	ret = data->ops->read(data->dev, MPL115_PADC);
	if (ret < 0)
		goto done;
	padc = ret >> 6;

	ret = data->ops->read(data->dev, MPL115_TADC);
	if (ret < 0)
		goto done;
	tadc = ret >> 6;

	/* see Freescale AN3785 */
	a1 = data->b1 + ((data->c12 * tadc) >> 11);
	y1 = (data->a0 << 10) + a1 * padc;

	/* compensated pressure with 4 fractional bits */
	pcomp = (y1 + ((data->b2 * (int) tadc) >> 1)) >> 9;

	kpa = pcomp * (115 - 50) / 1023 + (50 << 4);
	*val = kpa >> 4;
	*val2 = (kpa & 15) * (1000000 >> 4);
done:
	mutex_unlock(&data->lock);
	return ret;
}