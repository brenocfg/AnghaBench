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
struct vc_data {int vc_can_do_color; unsigned long vc_origin; int /*<<< orphan*/  vc_rows; int /*<<< orphan*/  vc_cols; scalar_t__ vc_screenbuf; TYPE_1__* vc_sw; } ;
struct module {int dummy; } ;
struct consw {struct module* owner; int /*<<< orphan*/  (* con_startup ) () ;} ;
struct con_driver {char* desc; int flag; int /*<<< orphan*/  last; int /*<<< orphan*/  first; struct consw const* con; } ;
struct TYPE_4__ {struct vc_data* d; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* con_deinit ) (struct vc_data*) ;} ;

/* Variables and functions */
 int CON_DRIVER_FLAG_INIT ; 
 int ENODEV ; 
 int MAX_NR_CON_DRIVER ; 
 int /*<<< orphan*/  WARN_CONSOLE_UNLOCKED () ; 
 int /*<<< orphan*/  __module_get (struct module*) ; 
 int /*<<< orphan*/  clear_buffer_attributes (struct vc_data*) ; 
 struct consw const** con_driver_map ; 
 scalar_t__ con_is_visible (struct vc_data*) ; 
 struct consw const* conswitchp ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct con_driver* registered_con_driver ; 
 int /*<<< orphan*/  save_screen (struct vc_data*) ; 
 int /*<<< orphan*/  set_origin (struct vc_data*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (struct vc_data*) ; 
 int /*<<< orphan*/  try_module_get (struct module*) ; 
 int /*<<< orphan*/  update_attr (struct vc_data*) ; 
 int /*<<< orphan*/  update_screen (struct vc_data*) ; 
 TYPE_2__* vc_cons ; 
 int /*<<< orphan*/  visual_init (struct vc_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_bind_con_driver(const struct consw *csw, int first, int last,
			   int deflt)
{
	struct module *owner = csw->owner;
	const char *desc = NULL;
	struct con_driver *con_driver;
	int i, j = -1, k = -1, retval = -ENODEV;

	if (!try_module_get(owner))
		return -ENODEV;

	WARN_CONSOLE_UNLOCKED();

	/* check if driver is registered */
	for (i = 0; i < MAX_NR_CON_DRIVER; i++) {
		con_driver = &registered_con_driver[i];

		if (con_driver->con == csw) {
			desc = con_driver->desc;
			retval = 0;
			break;
		}
	}

	if (retval)
		goto err;

	if (!(con_driver->flag & CON_DRIVER_FLAG_INIT)) {
		csw->con_startup();
		con_driver->flag |= CON_DRIVER_FLAG_INIT;
	}

	if (deflt) {
		if (conswitchp)
			module_put(conswitchp->owner);

		__module_get(owner);
		conswitchp = csw;
	}

	first = max(first, con_driver->first);
	last = min(last, con_driver->last);

	for (i = first; i <= last; i++) {
		int old_was_color;
		struct vc_data *vc = vc_cons[i].d;

		if (con_driver_map[i])
			module_put(con_driver_map[i]->owner);
		__module_get(owner);
		con_driver_map[i] = csw;

		if (!vc || !vc->vc_sw)
			continue;

		j = i;

		if (con_is_visible(vc)) {
			k = i;
			save_screen(vc);
		}

		old_was_color = vc->vc_can_do_color;
		vc->vc_sw->con_deinit(vc);
		vc->vc_origin = (unsigned long)vc->vc_screenbuf;
		visual_init(vc, i, 0);
		set_origin(vc);
		update_attr(vc);

		/* If the console changed between mono <-> color, then
		 * the attributes in the screenbuf will be wrong.  The
		 * following resets all attributes to something sane.
		 */
		if (old_was_color != vc->vc_can_do_color)
			clear_buffer_attributes(vc);
	}

	pr_info("Console: switching ");
	if (!deflt)
		pr_cont("consoles %d-%d ", first + 1, last + 1);
	if (j >= 0) {
		struct vc_data *vc = vc_cons[j].d;

		pr_cont("to %s %s %dx%d\n",
			vc->vc_can_do_color ? "colour" : "mono",
			desc, vc->vc_cols, vc->vc_rows);

		if (k >= 0) {
			vc = vc_cons[k].d;
			update_screen(vc);
		}
	} else {
		pr_cont("to %s\n", desc);
	}

	retval = 0;
err:
	module_put(owner);
	return retval;
}