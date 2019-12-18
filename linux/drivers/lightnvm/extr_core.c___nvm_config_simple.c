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
struct nvm_ioctl_create_simple {int lun_begin; int lun_end; } ;
struct nvm_geo {int all_luns; } ;
struct nvm_dev {struct nvm_geo geo; } ;

/* Variables and functions */
 int nvm_config_check_luns (struct nvm_geo*,int,int) ; 

__attribute__((used)) static int __nvm_config_simple(struct nvm_dev *dev,
			       struct nvm_ioctl_create_simple *s)
{
	struct nvm_geo *geo = &dev->geo;

	if (s->lun_begin == -1 && s->lun_end == -1) {
		s->lun_begin = 0;
		s->lun_end = geo->all_luns - 1;
	}

	return nvm_config_check_luns(geo, s->lun_begin, s->lun_end);
}