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
typedef  int /*<<< orphan*/  suffix ;
struct crypto_alg {char* cra_driver_name; int /*<<< orphan*/  cra_name; } ;

/* Variables and functions */
 int CRYPTO_MAX_ALG_NAME ; 
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int crypto_set_driver_name(struct crypto_alg *alg)
{
	static const char suffix[] = "-generic";
	char *driver_name = alg->cra_driver_name;
	int len;

	if (*driver_name)
		return 0;

	len = strlcpy(driver_name, alg->cra_name, CRYPTO_MAX_ALG_NAME);
	if (len + sizeof(suffix) > CRYPTO_MAX_ALG_NAME)
		return -ENAMETOOLONG;

	memcpy(driver_name + len, suffix, sizeof(suffix));
	return 0;
}