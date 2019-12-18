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
typedef  int /*<<< orphan*/  u16 ;
struct dsa_switch {struct b53_device* priv; } ;
struct b53_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int b53_arl_op (struct b53_device*,int /*<<< orphan*/ ,int,unsigned char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is5325 (struct b53_device*) ; 
 scalar_t__ is5365 (struct b53_device*) ; 

int b53_fdb_add(struct dsa_switch *ds, int port,
		const unsigned char *addr, u16 vid)
{
	struct b53_device *priv = ds->priv;

	/* 5325 and 5365 require some more massaging, but could
	 * be supported eventually
	 */
	if (is5325(priv) || is5365(priv))
		return -EOPNOTSUPP;

	return b53_arl_op(priv, 0, port, addr, vid, true);
}