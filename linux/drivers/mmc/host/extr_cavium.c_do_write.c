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
struct mmc_request {TYPE_1__* data; } ;
struct TYPE_2__ {int bytes_xfered; int blocks; int blksz; scalar_t__ error; } ;

/* Variables and functions */

__attribute__((used)) static void do_write(struct mmc_request *req)
{
	req->data->bytes_xfered = req->data->blocks * req->data->blksz;
	req->data->error = 0;
}