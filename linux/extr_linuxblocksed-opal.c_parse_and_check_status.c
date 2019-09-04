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
struct opal_dev {int /*<<< orphan*/  parsed; int /*<<< orphan*/  resp; int /*<<< orphan*/  pos; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_BUFFER_LENGTH ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  print_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int response_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int response_status (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_and_check_status(struct opal_dev *dev)
{
	int error;

	print_buffer(dev->cmd, dev->pos);

	error = response_parse(dev->resp, IO_BUFFER_LENGTH, &dev->parsed);
	if (error) {
		pr_debug("Couldn't parse response.\n");
		return error;
	}

	return response_status(&dev->parsed);
}