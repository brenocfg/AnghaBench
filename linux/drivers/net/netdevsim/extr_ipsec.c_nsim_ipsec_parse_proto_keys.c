#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {struct net_device* dev; } ;
struct xfrm_state {TYPE_2__* aead; TYPE_1__ xso; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int alg_icv_len; unsigned char* alg_key; int alg_key_len; char* alg_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int NSIM_IPSEC_AUTH_BITS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static int nsim_ipsec_parse_proto_keys(struct xfrm_state *xs,
				       u32 *mykey, u32 *mysalt)
{
	const char aes_gcm_name[] = "rfc4106(gcm(aes))";
	struct net_device *dev = xs->xso.dev;
	unsigned char *key_data;
	char *alg_name = NULL;
	int key_len;

	if (!xs->aead) {
		netdev_err(dev, "Unsupported IPsec algorithm\n");
		return -EINVAL;
	}

	if (xs->aead->alg_icv_len != NSIM_IPSEC_AUTH_BITS) {
		netdev_err(dev, "IPsec offload requires %d bit authentication\n",
			   NSIM_IPSEC_AUTH_BITS);
		return -EINVAL;
	}

	key_data = &xs->aead->alg_key[0];
	key_len = xs->aead->alg_key_len;
	alg_name = xs->aead->alg_name;

	if (strcmp(alg_name, aes_gcm_name)) {
		netdev_err(dev, "Unsupported IPsec algorithm - please use %s\n",
			   aes_gcm_name);
		return -EINVAL;
	}

	/* 160 accounts for 16 byte key and 4 byte salt */
	if (key_len > NSIM_IPSEC_AUTH_BITS) {
		*mysalt = ((u32 *)key_data)[4];
	} else if (key_len == NSIM_IPSEC_AUTH_BITS) {
		*mysalt = 0;
	} else {
		netdev_err(dev, "IPsec hw offload only supports 128 bit keys with optional 32 bit salt\n");
		return -EINVAL;
	}
	memcpy(mykey, key_data, 16);

	return 0;
}