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
struct psmouse {struct hgpk_data* private; } ;
struct hgpk_data {size_t mode; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char** hgpk_mode_names ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t attr_show_mode(struct psmouse *psmouse, void *data, char *buf)
{
	struct hgpk_data *priv = psmouse->private;

	return sprintf(buf, "%s\n", hgpk_mode_names[priv->mode]);
}