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
struct pnp_card {char* name; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct pnp_card* to_pnp_card (struct device*) ; 

__attribute__((used)) static ssize_t pnp_show_card_name(struct device *dmdev,
				  struct device_attribute *attr, char *buf)
{
	char *str = buf;
	struct pnp_card *card = to_pnp_card(dmdev);

	str += sprintf(str, "%s\n", card->name);
	return (str - buf);
}