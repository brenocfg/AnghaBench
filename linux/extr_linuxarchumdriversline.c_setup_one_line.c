#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_driver {int dummy; } ;
struct TYPE_4__ {scalar_t__ count; } ;
struct line {int valid; char* init_str; TYPE_2__ port; TYPE_1__* driver; } ;
struct device {int dummy; } ;
struct chan_opts {int dummy; } ;
struct TYPE_3__ {struct tty_driver* driver; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int parse_chan_pair (char*,struct line*,int,struct chan_opts const*,char**) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 struct device* tty_port_register_device (TYPE_2__*,struct tty_driver*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_device (struct tty_driver*,int) ; 

int setup_one_line(struct line *lines, int n, char *init,
		   const struct chan_opts *opts, char **error_out)
{
	struct line *line = &lines[n];
	struct tty_driver *driver = line->driver->driver;
	int err = -EINVAL;

	if (line->port.count) {
		*error_out = "Device is already open";
		goto out;
	}

	if (!strcmp(init, "none")) {
		if (line->valid) {
			line->valid = 0;
			kfree(line->init_str);
			tty_unregister_device(driver, n);
			parse_chan_pair(NULL, line, n, opts, error_out);
			err = 0;
		}
	} else {
		char *new = kstrdup(init, GFP_KERNEL);
		if (!new) {
			*error_out = "Failed to allocate memory";
			return -ENOMEM;
		}
		if (line->valid) {
			tty_unregister_device(driver, n);
			kfree(line->init_str);
		}
		line->init_str = new;
		line->valid = 1;
		err = parse_chan_pair(new, line, n, opts, error_out);
		if (!err) {
			struct device *d = tty_port_register_device(&line->port,
					driver, n, NULL);
			if (IS_ERR(d)) {
				*error_out = "Failed to register device";
				err = PTR_ERR(d);
				parse_chan_pair(NULL, line, n, opts, error_out);
			}
		}
		if (err) {
			line->init_str = NULL;
			line->valid = 0;
			kfree(new);
		}
	}
out:
	return err;
}