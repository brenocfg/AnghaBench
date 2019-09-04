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
struct rxe_dev {int /*<<< orphan*/  list; } ;
struct kernel_param {int dummy; } ;
typedef  int /*<<< orphan*/  intf ;

/* Variables and functions */
 int EINVAL ; 
 struct rxe_dev* get_rxe_by_name (char*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  rxe_remove (struct rxe_dev*) ; 
 int /*<<< orphan*/  rxe_remove_all () ; 
 int sanitize_arg (char const*,char*,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int rxe_param_set_remove(const char *val, const struct kernel_param *kp)
{
	int len;
	char intf[32];
	struct rxe_dev *rxe;

	len = sanitize_arg(val, intf, sizeof(intf));
	if (!len) {
		pr_err("add: invalid interface name\n");
		return -EINVAL;
	}

	if (strncmp("all", intf, len) == 0) {
		pr_info("rxe_sys: remove all");
		rxe_remove_all();
		return 0;
	}

	rxe = get_rxe_by_name(intf);

	if (!rxe) {
		pr_err("not configured on %s\n", intf);
		return -EINVAL;
	}

	list_del(&rxe->list);
	rxe_remove(rxe);

	return 0;
}