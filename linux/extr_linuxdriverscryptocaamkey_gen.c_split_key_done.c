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
typedef  scalar_t__ u32 ;
struct split_key_result {int /*<<< orphan*/  completion; scalar_t__ err; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  caam_jr_strstatus (struct device*,scalar_t__) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

void split_key_done(struct device *dev, u32 *desc, u32 err,
			   void *context)
{
	struct split_key_result *res = context;

#ifdef DEBUG
	dev_err(dev, "%s %d: err 0x%x\n", __func__, __LINE__, err);
#endif

	if (err)
		caam_jr_strstatus(dev, err);

	res->err = err;

	complete(&res->completion);
}