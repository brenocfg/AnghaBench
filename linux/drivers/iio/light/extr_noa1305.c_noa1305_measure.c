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
struct noa1305_priv {int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  NOA1305_REG_ALS_DATA_LSB ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int noa1305_measure(struct noa1305_priv *priv)
{
	__le16 data;
	int ret;

	ret = regmap_bulk_read(priv->regmap, NOA1305_REG_ALS_DATA_LSB, &data,
			       2);
	if (ret < 0)
		return ret;

	return le16_to_cpu(data);
}