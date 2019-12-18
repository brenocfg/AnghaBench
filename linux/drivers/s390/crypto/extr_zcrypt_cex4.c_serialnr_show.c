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
struct zcrypt_card {int /*<<< orphan*/  online; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cca_info {char* serial; } ;
struct ap_card {int /*<<< orphan*/  id; struct zcrypt_card* private; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  ci ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ ap_domain_index ; 
 int /*<<< orphan*/  cca_get_info (int /*<<< orphan*/ ,scalar_t__,struct cca_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cca_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 struct ap_card* to_ap_card (struct device*) ; 

__attribute__((used)) static ssize_t serialnr_show(struct device *dev,
			     struct device_attribute *attr,
			     char *buf)
{
	struct cca_info ci;
	struct ap_card *ac = to_ap_card(dev);
	struct zcrypt_card *zc = ac->private;

	memset(&ci, 0, sizeof(ci));

	if (ap_domain_index >= 0)
		cca_get_info(ac->id, ap_domain_index, &ci, zc->online);

	return snprintf(buf, PAGE_SIZE, "%s\n", ci.serial);
}