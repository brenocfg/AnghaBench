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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct fc_fdmi_attr_entry {scalar_t__ value; void* len; void* type; } ;

/* Variables and functions */
 size_t U16_MAX ; 
 scalar_t__ WARN_ON (int) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
csio_append_attrib(uint8_t **ptr, uint16_t type, void *val, size_t val_len)
{
	uint16_t len;
	struct fc_fdmi_attr_entry *ae = (struct fc_fdmi_attr_entry *)*ptr;

	if (WARN_ON(val_len > U16_MAX))
		return;

	len = val_len;

	ae->type = htons(type);
	len += 4;		/* includes attribute type and length */
	len = (len + 3) & ~3;	/* should be multiple of 4 bytes */
	ae->len = htons(len);
	memcpy(ae->value, val, val_len);
	if (len > val_len)
		memset(ae->value + val_len, 0, len - val_len);
	*ptr += len;
}