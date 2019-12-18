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
typedef  int /*<<< orphan*/  u8 ;
struct iucv_path {struct hvc_iucv_private* private; } ;
struct hvc_iucv_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hvc_iucv_hangup (struct hvc_iucv_private*) ; 

__attribute__((used)) static void hvc_iucv_path_severed(struct iucv_path *path, u8 *ipuser)
{
	struct hvc_iucv_private *priv = path->private;

	hvc_iucv_hangup(priv);
}