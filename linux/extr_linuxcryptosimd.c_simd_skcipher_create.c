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
struct simd_skcipher_alg {int dummy; } ;

/* Variables and functions */
 int CRYPTO_MAX_ALG_NAME ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 struct simd_skcipher_alg* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct simd_skcipher_alg* simd_skcipher_create_compat (char const*,char*,char const*) ; 
 int snprintf (char*,int,char*,char const*) ; 

struct simd_skcipher_alg *simd_skcipher_create(const char *algname,
					       const char *basename)
{
	char drvname[CRYPTO_MAX_ALG_NAME];

	if (snprintf(drvname, CRYPTO_MAX_ALG_NAME, "simd-%s", basename) >=
	    CRYPTO_MAX_ALG_NAME)
		return ERR_PTR(-ENAMETOOLONG);

	return simd_skcipher_create_compat(algname, drvname, basename);
}