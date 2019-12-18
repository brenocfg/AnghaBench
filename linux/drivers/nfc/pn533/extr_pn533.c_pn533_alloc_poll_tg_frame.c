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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct pn533 {int* gb; size_t gb_len; } ;

/* Variables and functions */
 size_t PN533_INIT_TARGET_DEP ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 struct sk_buff* pn533_alloc_skb (struct pn533*,unsigned int) ; 
 int* skb_put_data (struct sk_buff*,int*,size_t) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,size_t) ; 
 int* skb_put_zero (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *pn533_alloc_poll_tg_frame(struct pn533 *dev)
{
	struct sk_buff *skb;
	u8 *felica, *nfcid3;

	u8 *gbytes = dev->gb;
	size_t gbytes_len = dev->gb_len;

	u8 felica_params[18] = {0x1, 0xfe, /* DEP */
				0x0, 0x0, 0x0, 0x0, 0x0, 0x0, /* random */
				0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
				0xff, 0xff}; /* System code */

	u8 mifare_params[6] = {0x1, 0x1, /* SENS_RES */
			       0x0, 0x0, 0x0,
			       0x40}; /* SEL_RES for DEP */

	unsigned int skb_len = 36 + /*
				     * mode (1), mifare (6),
				     * felica (18), nfcid3 (10), gb_len (1)
				     */
			       gbytes_len +
			       1;  /* len Tk*/

	skb = pn533_alloc_skb(dev, skb_len);
	if (!skb)
		return NULL;

	/* DEP support only */
	skb_put_u8(skb, PN533_INIT_TARGET_DEP);

	/* MIFARE params */
	skb_put_data(skb, mifare_params, 6);

	/* Felica params */
	felica = skb_put_data(skb, felica_params, 18);
	get_random_bytes(felica + 2, 6);

	/* NFCID3 */
	nfcid3 = skb_put_zero(skb, 10);
	memcpy(nfcid3, felica, 8);

	/* General bytes */
	skb_put_u8(skb, gbytes_len);

	skb_put_data(skb, gbytes, gbytes_len);

	/* Len Tk */
	skb_put_u8(skb, 0);

	return skb;
}