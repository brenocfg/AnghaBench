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
struct scatterlist {int dummy; } ;
struct mmc_test_card {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int mmc_test_transfer (struct mmc_test_card*,struct scatterlist*,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mmc_test_verify_write(struct mmc_test_card *test)
{
	struct scatterlist sg;

	sg_init_one(&sg, test->buffer, 512);

	return mmc_test_transfer(test, &sg, 1, 0, 1, 512, 1);
}