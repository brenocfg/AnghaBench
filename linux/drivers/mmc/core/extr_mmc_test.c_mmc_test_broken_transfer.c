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
struct scatterlist {int dummy; } ;
struct mmc_test_card {TYPE_1__* card; int /*<<< orphan*/  buffer; } ;
struct mmc_request {struct mmc_command* stop; struct mmc_data* data; struct mmc_command* cmd; } ;
struct mmc_data {int dummy; } ;
struct mmc_command {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int mmc_test_check_broken_result (struct mmc_test_card*,struct mmc_request*) ; 
 int /*<<< orphan*/  mmc_test_prepare_broken_mrq (struct mmc_test_card*,struct mmc_request*,int) ; 
 int /*<<< orphan*/  mmc_test_prepare_mrq (struct mmc_test_card*,struct mmc_request*,struct scatterlist*,int,int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  mmc_test_wait_busy (struct mmc_test_card*) ; 
 int /*<<< orphan*/  mmc_wait_for_req (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int mmc_test_broken_transfer(struct mmc_test_card *test,
	unsigned blocks, unsigned blksz, int write)
{
	struct mmc_request mrq = {};
	struct mmc_command cmd = {};
	struct mmc_command stop = {};
	struct mmc_data data = {};

	struct scatterlist sg;

	mrq.cmd = &cmd;
	mrq.data = &data;
	mrq.stop = &stop;

	sg_init_one(&sg, test->buffer, blocks * blksz);

	mmc_test_prepare_mrq(test, &mrq, &sg, 1, 0, blocks, blksz, write);
	mmc_test_prepare_broken_mrq(test, &mrq, write);

	mmc_wait_for_req(test->card->host, &mrq);

	mmc_test_wait_busy(test);

	return mmc_test_check_broken_result(test, &mrq);
}