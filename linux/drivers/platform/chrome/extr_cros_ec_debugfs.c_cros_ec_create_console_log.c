#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ec_params_console_read_v1 {int dummy; } ;
struct cros_ec_dev {scalar_t__ cmd_offset; int /*<<< orphan*/  dev; TYPE_1__* ec_dev; } ;
struct TYPE_6__ {char* buf; scalar_t__ tail; scalar_t__ head; } ;
struct cros_ec_debugfs {int /*<<< orphan*/  log_poll_work; int /*<<< orphan*/  dir; int /*<<< orphan*/  log_wq; int /*<<< orphan*/  log_mutex; TYPE_3__ log_buffer; TYPE_2__* read_msg; struct cros_ec_dev* ec; } ;
struct TYPE_5__ {int version; int outsize; int insize; scalar_t__ command; } ;
struct TYPE_4__ {int max_response; } ;

/* Variables and functions */
 scalar_t__ EC_CMD_CONSOLE_READ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ LOG_SIZE ; 
 int S_IFREG ; 
 int /*<<< orphan*/  cros_ec_console_log_fops ; 
 int /*<<< orphan*/  cros_ec_console_log_work ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct cros_ec_debugfs*,int /*<<< orphan*/ *) ; 
 void* devm_kzalloc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ec_read_version_supported (struct cros_ec_dev*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ max (int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cros_ec_create_console_log(struct cros_ec_debugfs *debug_info)
{
	struct cros_ec_dev *ec = debug_info->ec;
	char *buf;
	int read_params_size;
	int read_response_size;

	/*
	 * If the console log feature is not supported return silently and
	 * don't create the console_log entry.
	 */
	if (!ec_read_version_supported(ec))
		return 0;

	buf = devm_kzalloc(ec->dev, LOG_SIZE, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	read_params_size = sizeof(struct ec_params_console_read_v1);
	read_response_size = ec->ec_dev->max_response;
	debug_info->read_msg = devm_kzalloc(ec->dev,
		sizeof(*debug_info->read_msg) +
			max(read_params_size, read_response_size), GFP_KERNEL);
	if (!debug_info->read_msg)
		return -ENOMEM;

	debug_info->read_msg->version = 1;
	debug_info->read_msg->command = EC_CMD_CONSOLE_READ + ec->cmd_offset;
	debug_info->read_msg->outsize = read_params_size;
	debug_info->read_msg->insize = read_response_size;

	debug_info->log_buffer.buf = buf;
	debug_info->log_buffer.head = 0;
	debug_info->log_buffer.tail = 0;

	mutex_init(&debug_info->log_mutex);
	init_waitqueue_head(&debug_info->log_wq);

	debugfs_create_file("console_log", S_IFREG | 0444, debug_info->dir,
			    debug_info, &cros_ec_console_log_fops);

	INIT_DELAYED_WORK(&debug_info->log_poll_work,
			  cros_ec_console_log_work);
	schedule_delayed_work(&debug_info->log_poll_work, 0);

	return 0;
}