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
typedef  scalar_t__ u16 ;
struct ipoib_dev_priv {scalar_t__ pkey_index; int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_PKEY_ASSIGNED ; 
 int /*<<< orphan*/  ipoib_pkey_dev_check_presence (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int update_child_pkey(struct ipoib_dev_priv *priv)
{
	u16 old_index = priv->pkey_index;

	priv->pkey_index = 0;
	ipoib_pkey_dev_check_presence(priv->dev);

	if (test_bit(IPOIB_PKEY_ASSIGNED, &priv->flags) &&
	    (old_index == priv->pkey_index))
		return 1;
	return 0;
}