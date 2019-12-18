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
struct libipw_network {int* rates; int* rates_ex; int /*<<< orphan*/  mode; int /*<<< orphan*/  rates_ex_len; int /*<<< orphan*/  rates_len; } ;
struct ipw_supported_rates {int* supported_rates; scalar_t__ num_rates; } ;
struct ipw_priv {int /*<<< orphan*/  rates_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_SCAN (char*,int,...) ; 
 int IPW_MAX_RATES ; 
 int LIBIPW_BASIC_RATE_MASK ; 
 int /*<<< orphan*/  ipw_is_rate_in_mask (struct ipw_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ipw_supported_rates*,int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipw_compatible_rates(struct ipw_priv *priv,
				const struct libipw_network *network,
				struct ipw_supported_rates *rates)
{
	int num_rates, i;

	memset(rates, 0, sizeof(*rates));
	num_rates = min(network->rates_len, (u8) IPW_MAX_RATES);
	rates->num_rates = 0;
	for (i = 0; i < num_rates; i++) {
		if (!ipw_is_rate_in_mask(priv, network->mode,
					 network->rates[i])) {

			if (network->rates[i] & LIBIPW_BASIC_RATE_MASK) {
				IPW_DEBUG_SCAN("Adding masked mandatory "
					       "rate %02X\n",
					       network->rates[i]);
				rates->supported_rates[rates->num_rates++] =
				    network->rates[i];
				continue;
			}

			IPW_DEBUG_SCAN("Rate %02X masked : 0x%08X\n",
				       network->rates[i], priv->rates_mask);
			continue;
		}

		rates->supported_rates[rates->num_rates++] = network->rates[i];
	}

	num_rates = min(network->rates_ex_len,
			(u8) (IPW_MAX_RATES - num_rates));
	for (i = 0; i < num_rates; i++) {
		if (!ipw_is_rate_in_mask(priv, network->mode,
					 network->rates_ex[i])) {
			if (network->rates_ex[i] & LIBIPW_BASIC_RATE_MASK) {
				IPW_DEBUG_SCAN("Adding masked mandatory "
					       "rate %02X\n",
					       network->rates_ex[i]);
				rates->supported_rates[rates->num_rates++] =
				    network->rates[i];
				continue;
			}

			IPW_DEBUG_SCAN("Rate %02X masked : 0x%08X\n",
				       network->rates_ex[i], priv->rates_mask);
			continue;
		}

		rates->supported_rates[rates->num_rates++] =
		    network->rates_ex[i];
	}

	return 1;
}