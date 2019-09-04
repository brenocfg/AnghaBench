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
struct sbefifo {scalar_t__ async_ffdc; scalar_t__ dead; TYPE_1__* fsi_dev; } ;
struct iov_iter {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EOVERFLOW ; 
 size_t be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  dev_vdbg (struct device*,char*,size_t,size_t) ; 
 int sbefifo_cleanup_hw (struct sbefifo*) ; 
 int /*<<< orphan*/  sbefifo_collect_async_ffdc (struct sbefifo*) ; 
 int sbefifo_do_command (struct sbefifo*,int /*<<< orphan*/  const*,size_t,struct iov_iter*) ; 
 int /*<<< orphan*/  sbefifo_request_reset (struct sbefifo*) ; 

__attribute__((used)) static int __sbefifo_submit(struct sbefifo *sbefifo,
			    const __be32 *command, size_t cmd_len,
			    struct iov_iter *response)
{
	struct device *dev = &sbefifo->fsi_dev->dev;
	int rc;

	if (sbefifo->dead)
		return -ENODEV;

	if (cmd_len < 2 || be32_to_cpu(command[0]) != cmd_len) {
		dev_vdbg(dev, "Invalid command len %zd (header: %d)\n",
			 cmd_len, be32_to_cpu(command[0]));
		return -EINVAL;
	}

	/* First ensure the HW is in a clean state */
	rc = sbefifo_cleanup_hw(sbefifo);
	if (rc)
		return rc;

	/* Look for async FFDC first if any */
	if (sbefifo->async_ffdc)
		sbefifo_collect_async_ffdc(sbefifo);

	rc = sbefifo_do_command(sbefifo, command, cmd_len, response);
	if (rc != 0 && rc != -EOVERFLOW)
		goto fail;
	return rc;
 fail:
	/*
	 * On failure, attempt a reset. Ignore the result, it will mark
	 * the fifo broken if the reset fails
	 */
        sbefifo_request_reset(sbefifo);

	/* Return original error */
	return rc;
}