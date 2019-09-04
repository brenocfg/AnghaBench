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
struct usdhi6_host {TYPE_1__* sg; int /*<<< orphan*/  offset; struct mmc_request* mrq; } ;
struct mmc_request {struct mmc_data* data; } ;
struct mmc_data {TYPE_1__* sg; int /*<<< orphan*/  blocks; } ;
struct TYPE_2__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  USDHI6_SD_SECCNT ; 
 int /*<<< orphan*/  usdhi6_write (struct usdhi6_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usdhi6_sg_prep(struct usdhi6_host *host)
{
	struct mmc_request *mrq = host->mrq;
	struct mmc_data *data = mrq->data;

	usdhi6_write(host, USDHI6_SD_SECCNT, data->blocks);

	host->sg = data->sg;
	/* TODO: if we always map, this is redundant */
	host->offset = host->sg->offset;
}