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
typedef  int u8 ;
struct nvmet_subsys {int /*<<< orphan*/  lock; } ;
struct nvmet_ns {int /*<<< orphan*/  nguid; scalar_t__ enabled; struct nvmet_subsys* subsys; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  nguid ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int hex_to_bin (char const) ; 
 int /*<<< orphan*/  isxdigit (char const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nvmet_ns* to_nvmet_ns (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_ns_device_nguid_store(struct config_item *item,
		const char *page, size_t count)
{
	struct nvmet_ns *ns = to_nvmet_ns(item);
	struct nvmet_subsys *subsys = ns->subsys;
	u8 nguid[16];
	const char *p = page;
	int i;
	int ret = 0;

	mutex_lock(&subsys->lock);
	if (ns->enabled) {
		ret = -EBUSY;
		goto out_unlock;
	}

	for (i = 0; i < 16; i++) {
		if (p + 2 > page + count) {
			ret = -EINVAL;
			goto out_unlock;
		}
		if (!isxdigit(p[0]) || !isxdigit(p[1])) {
			ret = -EINVAL;
			goto out_unlock;
		}

		nguid[i] = (hex_to_bin(p[0]) << 4) | hex_to_bin(p[1]);
		p += 2;

		if (*p == '-' || *p == ':')
			p++;
	}

	memcpy(&ns->nguid, nguid, sizeof(nguid));
out_unlock:
	mutex_unlock(&subsys->lock);
	return ret ? ret : count;
}