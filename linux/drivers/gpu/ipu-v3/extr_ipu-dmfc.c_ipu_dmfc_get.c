#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ipu_soc {struct ipu_dmfc_priv* dmfc_priv; } ;
struct ipu_dmfc_priv {struct dmfc_channel* channels; } ;
struct dmfc_channel {int dummy; } ;
struct TYPE_2__ {int ipu_channel; } ;

/* Variables and functions */
 int DMFC_NUM_CHANNELS ; 
 int /*<<< orphan*/  ENODEV ; 
 struct dmfc_channel* ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_1__* dmfcdata ; 

struct dmfc_channel *ipu_dmfc_get(struct ipu_soc *ipu, int ipu_channel)
{
	struct ipu_dmfc_priv *priv = ipu->dmfc_priv;
	int i;

	for (i = 0; i < DMFC_NUM_CHANNELS; i++)
		if (dmfcdata[i].ipu_channel == ipu_channel)
			return &priv->channels[i];
	return ERR_PTR(-ENODEV);
}