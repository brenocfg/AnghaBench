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
struct pcmcia_device_id {int match_flags; scalar_t__ manf_id; scalar_t__ card_id; scalar_t__ function; scalar_t__ device_no; scalar_t__ func_id; int /*<<< orphan*/  cisfile; int /*<<< orphan*/ * prod_id; } ;
struct pcmcia_device {scalar_t__ manf_id; scalar_t__ card_id; scalar_t__ func; scalar_t__ device_no; scalar_t__ func_id; int allow_func_id_match; scalar_t__ has_func_id; scalar_t__ has_card_id; scalar_t__ has_manf_id; scalar_t__* prod_id; TYPE_1__* socket; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int pcmcia_pfc; int /*<<< orphan*/  fake_cis; int /*<<< orphan*/  ops_mutex; } ;

/* Variables and functions */
 int PCMCIA_DEV_ID_MATCH_ANONYMOUS ; 
 int PCMCIA_DEV_ID_MATCH_CARD_ID ; 
 int PCMCIA_DEV_ID_MATCH_DEVICE_NO ; 
 int PCMCIA_DEV_ID_MATCH_FAKE_CIS ; 
 int PCMCIA_DEV_ID_MATCH_FUNCTION ; 
 int PCMCIA_DEV_ID_MATCH_FUNC_ID ; 
 int PCMCIA_DEV_ID_MATCH_MANF_ID ; 
 int PCMCIA_DEV_ID_MATCH_PROD_ID1 ; 
 int PCMCIA_DEV_ID_MATCH_PROD_ID2 ; 
 int PCMCIA_DEV_ID_MATCH_PROD_ID3 ; 
 int PCMCIA_DEV_ID_MATCH_PROD_ID4 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pcmcia_load_firmware (struct pcmcia_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int pcmcia_devmatch(struct pcmcia_device *dev,
				  const struct pcmcia_device_id *did)
{
	if (did->match_flags & PCMCIA_DEV_ID_MATCH_MANF_ID) {
		if ((!dev->has_manf_id) || (dev->manf_id != did->manf_id))
			return 0;
	}

	if (did->match_flags & PCMCIA_DEV_ID_MATCH_CARD_ID) {
		if ((!dev->has_card_id) || (dev->card_id != did->card_id))
			return 0;
	}

	if (did->match_flags & PCMCIA_DEV_ID_MATCH_FUNCTION) {
		if (dev->func != did->function)
			return 0;
	}

	if (did->match_flags & PCMCIA_DEV_ID_MATCH_PROD_ID1) {
		if (!dev->prod_id[0])
			return 0;
		if (strcmp(did->prod_id[0], dev->prod_id[0]))
			return 0;
	}

	if (did->match_flags & PCMCIA_DEV_ID_MATCH_PROD_ID2) {
		if (!dev->prod_id[1])
			return 0;
		if (strcmp(did->prod_id[1], dev->prod_id[1]))
			return 0;
	}

	if (did->match_flags & PCMCIA_DEV_ID_MATCH_PROD_ID3) {
		if (!dev->prod_id[2])
			return 0;
		if (strcmp(did->prod_id[2], dev->prod_id[2]))
			return 0;
	}

	if (did->match_flags & PCMCIA_DEV_ID_MATCH_PROD_ID4) {
		if (!dev->prod_id[3])
			return 0;
		if (strcmp(did->prod_id[3], dev->prod_id[3]))
			return 0;
	}

	if (did->match_flags & PCMCIA_DEV_ID_MATCH_DEVICE_NO) {
		dev_dbg(&dev->dev, "this is a pseudo-multi-function device\n");
		mutex_lock(&dev->socket->ops_mutex);
		dev->socket->pcmcia_pfc = 1;
		mutex_unlock(&dev->socket->ops_mutex);
		if (dev->device_no != did->device_no)
			return 0;
	}

	if (did->match_flags & PCMCIA_DEV_ID_MATCH_FUNC_ID) {
		int ret;

		if ((!dev->has_func_id) || (dev->func_id != did->func_id))
			return 0;

		/* if this is a pseudo-multi-function device,
		 * we need explicit matches */
		if (dev->socket->pcmcia_pfc)
			return 0;
		if (dev->device_no)
			return 0;

		/* also, FUNC_ID matching needs to be activated by userspace
		 * after it has re-checked that there is no possible module
		 * with a prod_id/manf_id/card_id match.
		 */
		mutex_lock(&dev->socket->ops_mutex);
		ret = dev->allow_func_id_match;
		mutex_unlock(&dev->socket->ops_mutex);

		if (!ret) {
			dev_dbg(&dev->dev,
				"skipping FUNC_ID match until userspace ACK\n");
			return 0;
		}
	}

	if (did->match_flags & PCMCIA_DEV_ID_MATCH_FAKE_CIS) {
		dev_dbg(&dev->dev, "device needs a fake CIS\n");
		if (!dev->socket->fake_cis)
			if (pcmcia_load_firmware(dev, did->cisfile))
				return 0;
	}

	if (did->match_flags & PCMCIA_DEV_ID_MATCH_ANONYMOUS) {
		int i;
		for (i = 0; i < 4; i++)
			if (dev->prod_id[i])
				return 0;
		if (dev->has_manf_id || dev->has_card_id || dev->has_func_id)
			return 0;
	}

	return 1;
}