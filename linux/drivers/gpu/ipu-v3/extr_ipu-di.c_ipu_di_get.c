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
struct ipu_soc {struct ipu_di** di_priv; } ;
struct ipu_di {int inuse; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 struct ipu_di* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_di_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct ipu_di *ipu_di_get(struct ipu_soc *ipu, int disp)
{
	struct ipu_di *di;

	if (disp > 1)
		return ERR_PTR(-EINVAL);

	di = ipu->di_priv[disp];

	mutex_lock(&ipu_di_lock);

	if (di->inuse) {
		di = ERR_PTR(-EBUSY);
		goto out;
	}

	di->inuse = true;
out:
	mutex_unlock(&ipu_di_lock);

	return di;
}