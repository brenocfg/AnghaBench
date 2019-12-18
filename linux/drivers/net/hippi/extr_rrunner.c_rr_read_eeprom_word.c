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
typedef  int /*<<< orphan*/  u32 ;
struct rr_private {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int rr_read_eeprom (struct rr_private*,size_t,unsigned char*,int) ; 

__attribute__((used)) static u32 rr_read_eeprom_word(struct rr_private *rrpriv,
			    size_t offset)
{
	__be32 word;

	if ((rr_read_eeprom(rrpriv, offset,
			    (unsigned char *)&word, 4) == 4))
		return be32_to_cpu(word);
	return 0;
}