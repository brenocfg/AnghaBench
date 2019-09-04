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
struct sk_buff {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void dump_skb (char * prefix, unsigned int vc, struct sk_buff * skb) {
#ifdef DEBUG_HORIZON
  unsigned int i;
  unsigned char * data = skb->data;
  PRINTDB (DBG_DATA, "%s(%u) ", prefix, vc);
  for (i=0; i<skb->len && i < 256;i++)
    PRINTDM (DBG_DATA, "%02x ", data[i]);
  PRINTDE (DBG_DATA,"");
#else
  (void) prefix;
  (void) vc;
  (void) skb;
#endif
  return;
}