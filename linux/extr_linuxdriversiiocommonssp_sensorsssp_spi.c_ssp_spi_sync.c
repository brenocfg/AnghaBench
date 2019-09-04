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
struct ssp_msg {int /*<<< orphan*/  length; } ;
struct ssp_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int EPERM ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  done ; 
 int ssp_do_transfer (struct ssp_data*,struct ssp_msg*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ssp_spi_sync(struct ssp_data *data, struct ssp_msg *msg,
			int timeout)
{
	DECLARE_COMPLETION_ONSTACK(done);

	if (WARN_ON(!msg->length))
		return -EPERM;

	return ssp_do_transfer(data, msg, &done, timeout);
}