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
struct rave_sp_eeprom {int /*<<< orphan*/  mutex; } ;
typedef  enum rave_sp_eeprom_access_type { ____Placeholder_rave_sp_eeprom_access_type } rave_sp_eeprom_access_type ;

/* Variables and functions */
 unsigned int RAVE_SP_EEPROM_PAGE_SIZE ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rave_sp_eeprom_page_access (struct rave_sp_eeprom*,int,unsigned int,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static int rave_sp_eeprom_access(struct rave_sp_eeprom *eeprom,
				 enum rave_sp_eeprom_access_type type,
				 unsigned int offset, u8 *data,
				 unsigned int data_len)
{
	unsigned int residue;
	unsigned int chunk;
	unsigned int head;
	int ret;

	mutex_lock(&eeprom->mutex);

	head    = offset % RAVE_SP_EEPROM_PAGE_SIZE;
	residue = data_len;

	do {
		/*
		 * First iteration, if we are doing an access that is
		 * not 32-byte aligned, we need to access only data up
		 * to a page boundary to avoid corssing it in
		 * rave_sp_eeprom_page_access()
		 */
		if (unlikely(head)) {
			chunk = RAVE_SP_EEPROM_PAGE_SIZE - head;
			/*
			 * This can only happen once per
			 * rave_sp_eeprom_access() call, so we set
			 * head to zero to process all the other
			 * iterations normally.
			 */
			head  = 0;
		} else {
			chunk = RAVE_SP_EEPROM_PAGE_SIZE;
		}

		/*
		 * We should never read more that 'residue' bytes
		 */
		chunk = min(chunk, residue);
		ret = rave_sp_eeprom_page_access(eeprom, type, offset,
						 data, chunk);
		if (ret)
			goto out;

		residue -= chunk;
		offset  += chunk;
		data    += chunk;
	} while (residue);
out:
	mutex_unlock(&eeprom->mutex);
	return ret;
}