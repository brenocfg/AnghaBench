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
struct most_snd_grp {int create_card; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int kstrtobool (char const*,int*) ; 
 int most_cfg_complete (char*) ; 
 struct most_snd_grp* to_most_snd_grp (struct config_item*) ; 

__attribute__((used)) static ssize_t most_snd_grp_create_card_store(struct config_item *item,
					      const char *page, size_t count)
{
	struct most_snd_grp *snd_grp = to_most_snd_grp(item);
	int ret;
	bool tmp;

	ret = kstrtobool(page, &tmp);
	if (ret)
		return ret;
	if (tmp) {
		ret = most_cfg_complete("sound");
		if (ret)
			return ret;
	}
	snd_grp->create_card = tmp;
	return count;
}